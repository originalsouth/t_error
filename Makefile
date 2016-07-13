.SILENT: demo
t_error: t_error.cc t_error.h
	g++ -Wall -Werror -std=c++11 -O3 -flto -o t_error t_error.cc
	g++ -Wall -Werror -std=c++11 -O3 -flto -D T_ERROR -o t_error_error t_error.cc
	g++ -Wall -Werror -std=c++11 -O3 -flto -D T_ERROR -D T_WARNING -o t_error_warning t_error.cc
	g++ -Wall -Werror -std=c++11 -O3 -flto -D T_ERROR -D T_WARNING -D T_DEBUG=1 -o t_error_debug-1 t_error.cc
	g++ -Wall -Werror -std=c++11 -O3 -flto -D T_ERROR -D T_WARNING -D T_DEBUG=2 -o t_error_debug-2 t_error.cc
	g++ -Wall -Werror -std=c++11 -O3 -flto -D T_ERROR -D T_WARNING -D T_DEBUG=3 -o t_error_debug-3 t_error.cc

demo: t_error
	echo "Normal"
	./t_error
	echo
	echo "Assert errors"
	-./t_error_error || true
	echo
	echo "Assert warnings (and errors)"
	-./t_error_warning || true
	echo
	echo "Assert debug messeges up until level 1 (error and warnings)"
	-./t_error_debug-1 || true
	echo
	echo "Assert debug messeges up until level 2 (error and warnings)"
	-./t_error_debug-2 || true
	echo
	echo "Assert debug messeges up until level 3 (error and warnings)"
	-./t_error_debug-3 || true
	echo

clean:
	-rm -f t_error t_error_error t_error_warning t_error_debug-1 t_error_debug-2 t_error_debug-3
