#! /usr/local/bin/bash


# merge all pdf file in Documents

TARGET_PATH= "/Users/richardyang/Documents"

gen_command(){
  target_dir=$TARGET_PATH
  min_depth=2
  want=("azw3", "pdf", "mobi")

  find $target_dir -name "*.azw3" -or -name "*.mobi" -or -name ""
}

find . -name "*.pdf" -depth 1 -print0 |xargs -0 -n 1 -I {} mv  \"{}\" ./books 