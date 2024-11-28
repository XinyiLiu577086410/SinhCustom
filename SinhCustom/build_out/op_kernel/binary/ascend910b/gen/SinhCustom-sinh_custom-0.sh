#!/bin/bash
echo "[Ascend910B1] Generating SinhCustom_00b2b0b8ab8f50db439d6cb44263785b ..."
opc $1 --main_func=sinh_custom --input_param=/home/ma-user/work/SinhCustom/SinhCustom/build_out/op_kernel/binary/ascend910b/gen/SinhCustom_00b2b0b8ab8f50db439d6cb44263785b_param.json --soc_version=Ascend910B1 --output=$2 --impl_mode="" --simplified_key_mode=0 --op_mode=dynamic

if ! test -f $2/SinhCustom_00b2b0b8ab8f50db439d6cb44263785b.json ; then
  echo "$2/SinhCustom_00b2b0b8ab8f50db439d6cb44263785b.json not generated!"
  exit 1
fi

if ! test -f $2/SinhCustom_00b2b0b8ab8f50db439d6cb44263785b.o ; then
  echo "$2/SinhCustom_00b2b0b8ab8f50db439d6cb44263785b.o not generated!"
  exit 1
fi
echo "[Ascend910B1] Generating SinhCustom_00b2b0b8ab8f50db439d6cb44263785b Done"
