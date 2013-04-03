set nicename=russian roulette.cgl
type "%nicename%" | grep times | sort > "sorted.%nicename%"
vim "sorted.%nicename%"