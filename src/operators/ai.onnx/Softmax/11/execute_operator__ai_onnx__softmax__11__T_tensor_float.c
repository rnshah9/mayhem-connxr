//this file was generated by ../../../../../../scripts/onnx_generator/OperatorTemplate.py
#include "operator__ai_onnx__softmax__11.h"
#include "tracing.h"
#include "utils.h"
#include <math.h>

static inline
void
softmax(float *in, float *out, int num) {

    float max = 0;
    for (int i = 0; i < num; i++) {
        if (in[i] > max) {
            max = in[i];
        }
    }

    float sum = 0;
    for (int i = 0; i < num; i++) {
        //reducing all arguments by fixed value (max) keeps ratio,
        //but expf will never return inf for large arguments
        float e = expf(in[i] - max);
        sum += e;
        out[i] = e;
    }
    for (int i = 0; i < num; i++) {
        out[i] /= sum;
    }
}

operator_status
execute_operator__ai_onnx__softmax__11__T_tensor_float(
    node_context *ctx
)
{
    TRACE_ENTRY(1);

    TRACE_NODE(2, true, ctx->onnx_node);

    /* UNCOMMENT AS NEEDED */

    Onnx__TensorProto *i_input = searchInputByName(ctx, 0);

    TRACE_TENSOR(2, true, i_input);

    context_operator__ai_onnx__softmax__11 *op_ctx = ctx->executer_context;

    // int64_t axis = op_ctx->axis;
    int64_t N = op_ctx->N;
    int64_t D = op_ctx->D;

    // TRACE_VAR(2, true, axis, "%" PRId64);
    TRACE_VAR(2, true, N, "%" PRId64);
    TRACE_VAR(2, true, D, "%" PRId64);

    Onnx__TensorProto *o_output = searchOutputByName(ctx, 0);

    TRACE_TENSOR(2, true, o_output);

    /* DO CALCULATION HERE */

    for (int n = 0; n < N; n++) {
        int offset = D*n;
        softmax(&i_input->float_data[offset], &o_output->float_data[offset], D);
    }

    TRACE_EXIT(1);

    /* CHANGE RETURN CODE IF THIS EXECUTER IS VALID */
    // return OP_ENOSYS;
    return OP_OK;
}