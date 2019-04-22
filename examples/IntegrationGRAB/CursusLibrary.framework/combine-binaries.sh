function message {
  echo "[CursusLibrary] combine-binaries.sh: $1"
}

framework_folder=$(dirname "$0")
fat_binary="$framework_folder/Versions/A/CursusLibrary"
armv7_binary="$framework_folder/Versions/A/CursusLibrary-armv7"
arm64_binary="$framework_folder/Versions/A/CursusLibrary-arm64"
iphonesimulator_binary="$framework_folder/Versions/A/CursusLibrary-iphonesimulator"

# message "lipo -create $armv7_binary $arm64_binary $iphonesimulator_binary -output $fat_binary"
if [ ! -e "$fat_binary" ] && [ -e "$armv7_binary" ] && [ -e "$arm64_binary" ] && [ -e "$iphonesimulator_binary" ]
then
  lipo -create "$armv7_binary" "$arm64_binary" "$iphonesimulator_binary" -output "$fat_binary"
  message "Combined framework binaries"
elif [ -e "$fat_binary" ]
then
  message "Failed to combine binaries: fat binary already exists"
elif [ ! -e "$armv7_binary" ]
then
  message "Failed to combine binaries: armv7 binary does not exist"
  message "path: $armv7_binary"
elif [ ! -e "$arm64_binary" ]
then
  message "Failed to combine binaries: arm64 does not exist"
elif [ ! -e "$iphonesimulator_binary" ]
then
  message "Failed to combine binaries: simulator does not exist"
fi
