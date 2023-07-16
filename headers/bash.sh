for i in {0..255}; do echo "$i: $(tput setaf $i)reg $(tput bold)bld$(tput sgr0) $(tput sgr 0 1)$(tput setaf $i)und$(tput sgr0)"; done
