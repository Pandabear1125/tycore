x86_64="https://developer.arm.com/-/media/Files/downloads/gnu/13.2.rel1/binrel/arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-eabi.tar.xz?rev=e434b9ea4afc4ed7998329566b764309&hash=688C370BF08399033CA9DE3C1CC8CF8E31D8C441"
AArch64="https://developer.arm.com/-/media/Files/downloads/gnu/13.2.rel1/binrel/arm-gnu-toolchain-13.2.rel1-aarch64-arm-none-eabi.tar.xz?rev=17baf091942042768d55c9a304610954&hash=7F32B9E3ADFAFC4F8F74C30EBBBFECEB1AC96B60"
x86_64_MacOS="https://developer.arm.com/-/media/Files/downloads/gnu/13.2.rel1/binrel/arm-gnu-toolchain-13.2.rel1-darwin-x86_64-arm-none-eabi.tar.xz?rev=a3d8c87bb0af4c40b7d7e0e291f6541b&hash=10927356ACA904E1A0122794E036E8DDE7D8435D"
Arm64="https://developer.arm.com/-/media/Files/downloads/gnu/13.2.rel1/binrel/arm-gnu-toolchain-13.2.rel1-darwin-arm64-arm-none-eabi.tar.xz?rev=73e10891de3d41e29e95ac2878742b74&hash=2FBE6B355E5A06A7A7A2BB51719BF0C2FAC4A138"

# where to store the compiler
OUTPUT=tools/compiler

TAR_NAME=arm-gnu-toolchain-13.2.rel1.tar.xz

# create a directory to store the compiler
mkdir -p $OUTPUT

# install the correct compiler based on the OS and architecture
if [[ "$(uname -s)" == "Linux" ]]; then
    if [[ $(uname -m) == "x86_64" ]]; then
        wget $x86_64 -O $TAR_NAME
    elif [[ $(uname -m) == "aarch64" ]]; then
        wget $AArch64 -O $TAR_NAME
    fi
elif [[ "$(uname -s)" == "Darwin" ]]; then
    if [[ $(uname -m) == "x86_64" ]]; then
        wget $x86_64_MacOS -O $TAR_NAME
    elif [[ $(uname -m) == "arm64" ]]; then
        wget $Arm64 -O $TAR_NAME
    fi
fi

# remove the downloaded tar files
tar -xf $TAR_NAME -C $OUTPUT
mv $OUTPUT/arm-gnu-toolchain* $OUTPUT/arm-gnu-toolchain
rm $TAR_NAME