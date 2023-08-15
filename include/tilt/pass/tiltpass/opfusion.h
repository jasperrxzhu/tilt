#ifndef INCLUDE_TILT_PASSS_TILTPASS_OPFUSION_H_
#define INCLUDE_TILT_PASSS_TILTPASS_OPFUSION_H_

#include <vector>

#include "tilt/pass/irgen.h"

using namespace std;

namespace tilt {

/**********************************************
 * Class for performing a single TiLT operator fusion
 * root_op is the Op on which fusion is being applied
 * to_fuse_sym/to_fuse_op are the Sym/Expr which are being fused
 * Assumptions for fusion:
    * root_op has to_fuse_sym as an input Sym
    * root_op has a Sym corresponding to to_fuse_op[_pt(0)]
    * root_op has no Exprs of the form to_fuse_op[_pt(x)] where x is non-zero
**********************************************/

class OpFusion : public Visitor {
public:
    OpFusion(Op root_op, Sym to_fuse_sym, Op to_fuse_op);

    void fuse(void);

private:
    void Visit(const Symbol& symbol) final {}
    void Visit(const Out& expr) final { throw runtime_error("Invalid expression"); }
    void Visit(const Beat& expr) final { throw runtime_error("Invalid expression"); }
    void Visit(const Call& expr) final {}
    void Visit(const IfElse& expr) final {}
    void Visit(const Select& expr) final {}
    void Visit(const Get& expr) final {}
    void Visit(const New& expr) final {}
    void Visit(const Exists& expr) final {}
    void Visit(const ConstNode& expr) final {}
    void Visit(const Cast& expr) final {}
    void Visit(const NaryExpr& expr) final {}
    void Visit(const SubLStream& expr) final {}
    void Visit(const Element& expr) final {}
    void Visit(const OpNode& expr) final {}
    void Visit(const Reduce& expr) final {}
    void Visit(const Fetch& expr) final { throw runtime_error("Invalid expression"); }
    void Visit(const Read& expr) final { throw runtime_error("Invalid expression"); }
    void Visit(const Write& expr) final { throw runtime_error("Invalid expression"); }
    void Visit(const Advance& expr) final { throw runtime_error("Invalid expression"); }
    void Visit(const GetCkpt& expr) final { throw runtime_error("Invalid expression"); }
    void Visit(const GetStartIdx& expr) final { throw runtime_error("Invalid expression"); }
    void Visit(const GetEndIdx& expr) final { throw runtime_error("Invalid expression"); }
    void Visit(const GetStartTime& expr) final { throw runtime_error("Invalid expression"); }
    void Visit(const GetEndTime& expr) final { throw runtime_error("Invalid expression"); }
    void Visit(const CommitData& expr) final { throw runtime_error("Invalid expression"); }
    void Visit(const CommitNull& expr) final { throw runtime_error("Invalid expression"); }
    void Visit(const AllocRegion& expr) final { throw runtime_error("Invalid expression"); }
    void Visit(const MakeRegion& expr) final { throw runtime_error("Invalid expression"); }
    void Visit(const LoopNode& expr) final { throw runtime_error("Invalid expression"); }

    Expr eval(const Expr expr)
    {
        expr->Accept(*this);
        return val;
    }

    const Op root_op;
    const Sym to_fuse_sym;
    const Op to_fuse_op;

    /* fields determined by ctor */
    vector<Sym>::iterator input_sym_it;
    Sym to_replace_sym;

    Expr val;
};

}  // namespace tilt

#endif  // INCLUDE_TILT_PASSS_TILTPASS_OPFUSION_H_