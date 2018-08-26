all: Servidor Cliente


Servidor: Servidor.java
	javac -cp ".:../kryonet/jar/kryonet-2.21-all.jar:SomeResponse.java:SomeRequest.java" Servidor.java
Cliente: Cliente.java
	javac -cp ".:../kryonet/jar/kryonet-2.21-all.jar:SomeResponse.java:SomeRequest.java" Cliente.java

clean:
	rm *.class
