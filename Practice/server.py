from xmlrpc.server import SimpleXMLRPCServer 

def greet(name):
    return "Hello" + name + "!"
    
port = 8000
server = SimpleXMLRPCServer(("localhost", port),logRequests=False)
server.register_function(greet, 'greet_rpc')

try:
    print("server listening on port",port)
    server.serve_forever()
except:
    print("Exit")