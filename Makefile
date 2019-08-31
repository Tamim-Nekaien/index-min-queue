prim_mst: edge.h graph.h vertex.h index_min_pq.h prim_mst.cc
	g++ -Wall -Werror -std=c++11 -o prim_mst edge.h graph.h vertex.h index_min_pq.h prim_mst.cc

#test_index_min_pq: test_index_min_pq.cc index_min_pq.h
#	g++ -Wall -g -ggdb3 -Werror -std=c++11 -o test_index_min_pq test_index_min_pq.cc -pthread -lgtest

clean:
	rm -f prim_mst
	#rm -f  test_index_min_pq
