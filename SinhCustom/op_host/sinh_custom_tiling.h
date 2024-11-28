
#include "register/tilingdata_base.h"

namespace optiling {
BEGIN_TILING_DATA_DEF(SinhCustomTilingData)
  //考生自行定义tiling结构体成员变量
  TILING_DATA_FIELD_DEF(uint32_t, blockDim);
  TILING_DATA_FIELD_DEF(uint32_t, tileNum);
  TILING_DATA_FIELD_DEF(uint32_t, bufferNum);

  TILING_DATA_FIELD_DEF(uint32_t, totalLength);
  TILING_DATA_FIELD_DEF(uint32_t, blockLength);
  TILING_DATA_FIELD_DEF(uint32_t, tileLength);
END_TILING_DATA_DEF;

REGISTER_TILING_DATA_CLASS(SinhCustom, SinhCustomTilingData)
}
