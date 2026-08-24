cap=$(xset -q | grep Caps | awk '{print $4}')
if [ $cap = "on" ] ; then
	echo "Caps: ON"
else
	echo "Caps: off"
fi;
