#!/bin/bash
# Publish firmware to M5Burner for all device targets.

set -e

VERSION="${1:?Usage: $0 <version>}"
TEMPLATE_DIR="m5burner"

# Firmware IDs (from M5Burner)
declare -A FIDS=(
    ["stickc"]="d5afd7142b18fd2bcd2e101e736fa9c2"
    ["sticks3"]="c027b8e53fb1110d284231ce4d13834a"
    ["cardputer"]="fef12bcfc2ff4dd9078f8d629ac64cd7"
)

echo "Publishing firmware v$VERSION to M5Burner..."
echo ""

for TEMPLATE in "$TEMPLATE_DIR"/*.json; do
    KEY=$(basename "$TEMPLATE" .json)
    FID="${FIDS[$KEY]}"
    PAYLOAD="payload_${KEY}.json"

    if [ -z "$FID" ]; then
        echo "WARNING: No FID found for '$KEY', skipping."
        continue
    fi

    echo "--- $KEY (fid=$FID) ---"

    sed "s/__VERSION__/$VERSION/g" "$TEMPLATE" > "$PAYLOAD"

    npx -y m5-burner update-firmware "$FID" "$VERSION" "$PAYLOAD"

    rm -f "$PAYLOAD"
    echo ""
done

echo "All devices published successfully!"
