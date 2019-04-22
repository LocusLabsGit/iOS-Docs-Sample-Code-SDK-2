set -e

framework_folder=$(dirname "$0")
fat_binary="$framework_folder/Versions/A/CursusLibrary"
armv7_binary="$framework_folder/Versions/A/CursusLibrary-armv7"
arm64_binary="$framework_folder/Versions/A/CursusLibrary-arm64"
iphonesimulator_binary="$framework_folder/Versions/A/CursusLibrary-iphonesimulator"

if [ ! -e "$fat_binary" ]; then
  echo "No CursusLibrary binary found"
  exit 1
fi

# Create iphoneos binaries
lipo -extract armv7 -output "$armv7_binary" "$fat_binary"
echo "Created armv7 binary: $armv7_binary"
lipo -extract arm64 -output "$arm64_binary" "$fat_binary"
echo "Created arm64 binary: $arm64_binary"

# Create iphonesimulator binary
lipo -remove armv7 -output "$iphonesimulator_binary" "$fat_binary"
lipo -remove arm64 -output "$iphonesimulator_binary" "$iphonesimulator_binary"
echo "Created iphonesimulator binary: $iphonesimulator_binary"

exit 0
