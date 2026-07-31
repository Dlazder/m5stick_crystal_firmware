#!/bin/bash
# Publish firmware to M5Burner for all device targets.
set -e

VERSION="${1:?Usage: $0 <version>}"
TEMPLATE_DIR="m5burner"

echo "Publishing firmware v$VERSION to M5Burner..."
echo ""

for TEMPLATE in "$TEMPLATE_DIR"/*.json; do
    KEY=$(basename "$TEMPLATE" .json)
    PAYLOAD="payload_${KEY}.json"

    echo "--- $KEY ---"

    sed "s/__VERSION__/$VERSION/g" "$TEMPLATE" > "$PAYLOAD"

    npx -y m5-burner publish-firmware "$PAYLOAD"

    rm -f "$PAYLOAD"
    echo ""
done

echo "All devices published successfully!"
