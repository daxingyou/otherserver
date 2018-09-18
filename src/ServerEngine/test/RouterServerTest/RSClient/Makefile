all:
	protoc --cpp_out=./  RouterServer.proto
	protoc --cpp_out=./  GameServer.proto
	protoc --cpp_out=./  GameServerExt.proto
	g++ -g Client.cpp RouterServer.pb.cc GameServer.pb.cc -lzmq -l:libprotobuf.a -o Client
	
clean:
	rm RouterServer.pb.h RouterServer.pb.cc
	rm -rf Client
