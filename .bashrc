# Source default setting
[ -f /etc/bashrc ] && . /etc/bashrc

# User environment PATH
export PATH
umask 0027
. /home/ma-user/anaconda3/etc/profile.d/conda.sh
umask 027
export PS1='[\u \W]$'
conda activate $ENV_NAME
sh /modelarts/authoring/script/entrypoint/common/terminal_tips.sh
HISTSIZE=5000
export LD_LIBRARY_PATH=/home/ma-user/work/Ascend/ascend-toolkit/latest/lib64:/usr/local/lib/:/usr/local/Ascend/toolbox/latest/Ascend-DMI/lib64:/usr/lib/aarch64-linux-gnu/hdf5/serial:/usr/local/Ascend/driver/lib64:/usr/local/Ascend/driver/lib64/common:/usr/local/Ascend/driver/lib64/driver:/usr/local/Ascend/ascend-toolkit/latest/lib64:/usr/local/Ascend/ascend-toolkit/latest/compiler/lib64/plugin/opskernel:/usr/local/Ascend/ascend-toolkit/latest/compiler/lib64/plugin/nnengine:/usr/local/Ascend/ascend-toolkit/latest/opp/built-in/op_impl/ai_core/tbe/op_tiling/lib/:/usr/local/seccomponent/lib/:/usr/local/seccomponent/lib/openssl/:/usr/local/mindspore-lite/tools/converter/lib:/usr/local/mindspore-lite/runtime/lib:/usr/lib64:/home/ma-user/anaconda3/envs/MindSpore/lib

source /home/ma-user/work/Ascend/ascend-toolkit/set_env.sh
export PATH=/home/ma-user/work/cmake-3.28.3-linux-aarch64/bin:$HOME/Ascend/ascend-toolkit/latest//python/site-packages/bin:$PATH
ln -s $(realpath /home/ma-user/work/Ascend) ~/Ascend


