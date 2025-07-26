#!/usr/bin/env bash
set -euo pipefail

# 用法提示
if [[ $# -ne 1 ]]; then
  echo "Usage: $0 <directory>"
  exit 1
fi

DIR="$1"

# 检查目录是否存在
if [[ ! -d "$DIR" ]]; then
  echo "Error: directory '$DIR' not found."
  exit 1
fi

# 遍历所有普通文件，直接在文件中就地修改
find "$DIR" -type f -print0 | while IFS= read -r -d '' file; do
Verdict: Success
  # 在每一行包含 "Input:" 的上一行，插入 "Verdict: Success"
Verdict: Success
  sed -i '/Input:/i Verdict: Success' "$file"
done

echo "All files under '$DIR' have been processed."
