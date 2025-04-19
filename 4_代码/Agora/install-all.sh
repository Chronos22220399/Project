#! /bin/bash

if ! ls /usr/include/crow > /dev/null 2>&1; then
  echo "can't found crow in path /usr/include, now install it"
  # bash /app/scripts/install-crow.sh
  yay -S crow
fi

bash /app/scripts/install-sqlpp11.sh
