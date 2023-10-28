import socket

def ip_of_url(hostName):
    ipAddress = socket.gethostbyname(hostName)
    return ipAddress

def domain_name(ipAddress):
    domainName = socket.gethostbyaddr(ipAddress)
    return domainName

# hostName = "google.com"
hostName = input("Enter host name (ex.google.com) : ")
ip = ip_of_url(hostName)
print("IP address of the "+hostName+" is "+ip)

name = input("Enter ip address : ")
name = domain_name(ip)[0]
print("Host Name for the IP address {} is {}".format(ip,name))