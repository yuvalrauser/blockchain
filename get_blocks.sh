#!/bin/bash

if [ -z "$1" ]; then
  echo "Usage: ./get_blocks.sh <number of blocks>"
  exit 1
fi

count=$1
output_file="blockchain_data.txt"
> "$output_file"

latest_json=$(curl -s https://api.blockcypher.com/v1/btc/main)
current_hash=$(echo "$latest_json" | grep '"hash"' | cut -d '"' -f4)

for ((i = 0; i < count; i++))
do
  echo "Downloading block $((i+1))..."

  block_json=$(curl -s https://api.blockcypher.com/v1/btc/main/blocks/$current_hash)

  hash=$(echo "$block_json" | grep '"hash"' | cut -d '"' -f4)
  height=$(echo "$block_json" | grep '"height"' | cut -d ':' -f2 | cut -d ',' -f1)
  total=$(echo "$block_json" | grep '"total"' | cut -d ':' -f2 | cut -d ',' -f1)
  time=$(echo "$block_json" | grep '"time"' | cut -d '"' -f4)
  received=$(echo "$block_json" | grep '"received_time"' | cut -d '"' -f4)
  relayed=$(echo "$block_json" | grep '"relayed_by"' | cut -d '"' -f4)s
  prev_block=$(echo "$block_json" | grep '"prev_block"' | cut -d '"' -f4)

  {
    echo "hash: $hash"
    echo "height: $height"
    echo "total: $total"
    echo "time: $time"
    echo "received_time: $received"
    echo "relayed_by: $relayed"
    echo "prev_block: $prev_block"
  } >> "$output_file"

  if [ $i -lt $((count - 1)) ]; then
    {
      echo "                              |"
      echo "                              |"
      echo "                              |"
      echo "                              V"
    } >> "$output_file"
  fi

  current_hash=$prev_block
done
