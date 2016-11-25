cd bin

set /p filename="emter proto file name (note don't need .proto): "



protoc -I=../ProtoSource --cpp_out=../ProtroHeaders ../ProtoSource/%filename%.proto
