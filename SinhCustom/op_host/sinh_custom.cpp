
#include "sinh_custom_tiling.h"
#include "register/op_def_registry.h"

constexpr int32_t BLOCK_DIM = 64;                                     // num of core used
constexpr int32_t TILE_NUM = 8;                                       // split data into 8 tiles for each core
constexpr int32_t BUFFER_NUM = 2;                                     // tensor num for each queue


namespace optiling {
static ge::graphStatus TilingFunc(gert::TilingContext* context)
{
    SinhCustomTilingData tiling;
    //考生自行填充
    uint32_t totalLength = context->GetInputTensor(0)->GetShapeSize();
    const int32_t blockLength = totalLength / BLOCK_DIM;            // length computed of each core
    const int32_t tileLength = blockLength / TILE_NUM / BUFFER_NUM; // separate to 2 parts, due to double buffer
    context->SetBlockDim(BLOCK_DIM);
    
    tiling.set_blockDim(BLOCK_DIM);
    tiling.set_tileNum(TILE_NUM);
    tiling.set_bufferNum(BUFFER_NUM);

    tiling.set_totalLength(totalLength);
    tiling.set_blockLength(blockLength);
    tiling.set_tileLength(tileLength);

    tiling.SaveToBuffer(context->GetRawTilingData()->GetData(),
                         context->GetRawTilingData()->GetCapacity());
    context->GetRawTilingData()->SetDataSize(tiling.GetDataSize());
    // context->SetTilingKey(1);
    // size_t *currentWorkspace = context->GetWorkspaceSizes(1);
    // currentWorkspace[0] = 0;
    return ge::GRAPH_SUCCESS;
}
}


namespace ge {
static ge::graphStatus InferShape(gert::InferShapeContext* context)
{
    const gert::Shape* x1_shape = context->GetInputShape(0);
    gert::Shape* y_shape = context->GetOutputShape(0);
    *y_shape = *x1_shape;
    return GRAPH_SUCCESS;
}
}


namespace ops {
class SinhCustom : public OpDef {
public:
    explicit SinhCustom(const char* name) : OpDef(name)
    {
        this->Input("x")
            .ParamType(REQUIRED)
            .DataType({ge::DT_FLOAT16})
            .Format({ge::FORMAT_ND})
            .UnknownShapeFormat({ge::FORMAT_ND});
        this->Output("y")
            .ParamType(REQUIRED)
            .DataType({ge::DT_FLOAT16})
            .Format({ge::FORMAT_ND})
            .UnknownShapeFormat({ge::FORMAT_ND});

        this->SetInferShape(ge::InferShape);

        this->AICore()
            .SetTiling(optiling::TilingFunc);
        this->AICore().AddConfig("ascend910b");
    }
};

OP_ADD(SinhCustom);
}
