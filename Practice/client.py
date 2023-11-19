import xmlrpc.client 
proxy = xmlrpc.client.ServerProxy("http://localhost:8000/")

while(True):
    c=int(input("1.Message\n2.Exit"))
    if(c == 1):
        a = input("Enter message : ")
        print(str(proxy.greet_rpc(a)))
    else:
        break