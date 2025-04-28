#! /bin/bash

check_and_install() {
  local check_path="$1"
  local install_cmd="$2"
  
  if ! ls "${check_path}" > /dev/null 2>&1; then
    echo "can't found ${check_path}, now install..."
    eval "${install_cmd}" || {
      echo "Install failed"
      exit 1
    }
  else 
    echo "${check_path} exists, continue..."
  fi
}

# crow
check_and_install "/usr/include/crow" "yay -S crow"

# zlib
check_and_install "/usr/include/zlib.h" "pacman -S --nonconfirm zlib"

# sqlpp11
check_and_install "/usr/local/include/sqlpp11" "bash ./scripts/install-sqlpp11.sh"

# sqdlog
check_and_install "/usr/include/spdlog" "pacman -S --nonconfirm spdlog"

# yazi
check_and_install "/bin/yazi" "pacman -S --nonconfirm yazi"
