#include <map>
#include <memory>
#include <vector>

#include "tilt/base/log.h"
#include "tilt/builder/tilder.h"
#include "tilt/ir/lstream.h"
#include "tilt/ir/node.h"
#include "tilt/pass/tiltpass/opfusion.h"

using namespace std;
using namespace tilt;
using namespace tilt::tilder;

OpFusion::OpFusion(Op root_op, Sym to_fuse_sym, Op to_fuse_op) :
    root_op(root_op), to_fuse_sym(to_fuse_sym), to_fuse_op(to_fuse_op)
{
    /* check that to_fuse_sym is an input to root_op */
    bool is_input = false;
    for (auto it = root_op->inputs.begin(); it != root_op->inputs.end(); ++it) {
        if (*it == to_fuse_sym) {
            this->input_sym_it = it;
            is_input = true;
            break;
        }
    }
    ASSERT(is_input);

    /* check that root_op has a symbol with expr corresponding to to_fuse_sym[_pt(0)] */
    bool has_sym = false;
    shared_ptr<Element> elem_expr;
    for (auto it = root_op->syms.begin(); it != root_op->syms.end(); ++it) {
        elem_expr = dynamic_pointer_cast<Element>(it->second);
        if (elem_expr && (*(elem_expr->lstream) == *(to_fuse_sym)) && (elem_expr->pt.offset == 0)) {
            has_sym = true;
            this->to_replace_sym = it->first;
            break;
        }
    }
    ASSERT(has_sym);
}

void OpFusion::fuse(void)
{
    // replace inputs
    auto inputs_it = root_op->inputs.insert(input_sym_it, to_fuse_op->inputs.begin(), to_fuse_op->inputs.end());
    root_op->inputs.erase(inputs_it + to_fuse_op->inputs.size());

    // add symbols of to_fuse_op to root_op and update to_replace_sym expression
    for (auto map_it = to_fuse_op->syms.begin(); map_it != to_fuse_op->syms.end(); ++map_it) {
        root_op->syms[map_it->first] = map_it->second;
    }
    root_op->syms[to_replace_sym] = to_fuse_op->output;

    // update predicates
    root_op->pred = eval(root_op->pred);
}
