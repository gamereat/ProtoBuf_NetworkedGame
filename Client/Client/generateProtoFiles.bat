
@echo off

set /P fileName=Name of Protro3 file to Generate : 
 

cd Protro3/bin


protoc -I=../ProtoSource --cpp_out=../../ProtroHeaders ../ProtoSource/%fileName%.proto


