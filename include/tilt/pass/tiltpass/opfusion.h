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
    Expr visit(const Symbol&) { throw runtime_error("Invalid expression"); }
    Expr visit(const Out&) { throw runtime_error("Invalid expression"); }
    Expr visit(const Beat&) { throw runtime_error("Invalid expression"); }
    Expr visit(const Call&) { throw runtime_error("Invalid expression"); }
    Expr visit(const IfElse&) { throw runtime_error("Invalid expression"); }
    Expr visit(const Select&) { throw runtime_error("Invalid expression"); }
    Expr visit(const Get&) { throw runtime_error("Invalid expression"); }
    Expr visit(const New&) { throw runtime_error("Invalid expression"); }
    Expr visit(const Exists&);
    Expr visit(const ConstNode&) { throw runtime_error("Invalid expression"); }
    Expr visit(const Cast&) { throw runtime_error("Invalid expression"); }
    Expr visit(const NaryExpr&) { throw runtime_error("Invalid expression"); }
    Expr visit(const SubLStream&) { throw runtime_error("Invalid expression"); }
    Expr visit(const Element&) { throw runtime_error("Invalid expression"); }
    Expr visit(const OpNode&) { throw runtime_error("Invalid expression"); }
    Expr visit(const Reduce&) { throw runtime_error("Invalid expression"); }
    Expr visit(const Fetch&) { throw runtime_error("Invalid expression"); }
    Expr visit(const Read&) { throw runtime_error("Invalid expression"); }
    Expr visit(const Write&) { throw runtime_error("Invalid expression"); }
    Expr visit(const Advance&) { throw runtime_error("Invalid expression"); }
    Expr visit(const GetCkpt&) { throw runtime_error("Invalid expression"); }
    Expr visit(const GetStartIdx&) { throw runtime_error("Invalid expression"); }
    Expr visit(const GetEndIdx&) { throw runtime_error("Invalid expression"); }
    Expr visit(const GetStartTime&) { throw runtime_error("Invalid expression"); }
    Expr visit(const GetEndTime&) { throw runtime_error("Invalid expression"); }
    Expr visit(const CommitData&) { throw runtime_error("Invalid expression"); }
    Expr visit(const CommitNull&) { throw runtime_error("Invalid expression"); }
    Expr visit(const AllocRegion&) { throw runtime_error("Invalid expression"); }
    Expr visit(const MakeRegion&) { throw runtime_error("Invalid expression"); }
    Expr visit(const LoopNode&) { throw runtime_error("Invalid expression"); }

    void Visit(const Symbol& expr) final { val = visit(expr); }
    void Visit(const Out& expr) final { val = visit(expr); }
    void Visit(const Beat& expr) final { val = visit(expr); }
    void Visit(const IfElse& expr) final { val = visit(expr); }
    void Visit(const Select& expr) final { val = visit(expr); }
    void Visit(const Get& expr) final { val = visit(expr); }
    void Visit(const New& expr) final { val = visit(expr); }
    void Visit(const Exists& expr) final { val = visit(expr); }
    void Visit(const ConstNode& expr) final { val = visit(expr); }
    void Visit(const Cast& expr) final { val = visit(expr); }
    void Visit(const NaryExpr& expr) final { val = visit(expr); }
    void Visit(const SubLStream& expr) final { val = visit(expr); }
    void Visit(const Element& expr) final { val = visit(expr); }
    void Visit(const OpNode& expr) final { val = visit(expr); }
    void Visit(const Reduce& expr) final { val = visit(expr); }
    void Visit(const Fetch& expr) final { val = visit(expr); }
    void Visit(const Read& expr) final { val = visit(expr); }
    void Visit(const Write& expr) final { val = visit(expr); }
    void Visit(const Advance& expr) final { val = visit(expr); }
    void Visit(const GetCkpt& expr) final { val = visit(expr); }
    void Visit(const GetStartIdx& expr) final { val = visit(expr); }
    void Visit(const GetEndIdx& expr) final { val = visit(expr); }
    void Visit(const GetStartTime& expr) final { val = visit(expr); }
    void Visit(const GetEndTime& expr) final { val = visit(expr); }
    void Visit(const CommitData& expr) final { val = visit(expr); }
    void Visit(const CommitNull& expr) final { val = visit(expr); }
    void Visit(const AllocRegion& expr) final { val = visit(expr); }
    void Visit(const MakeRegion& expr) final { val = visit(expr); }
    void Visit(const Call& expr) final { val = visit(expr); }
    void Visit(const LoopNode& expr) final { val = visit(expr); }

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