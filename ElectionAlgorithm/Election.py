
# ----> Sarthak Nirgude <----
#         ◉_◉
# ----|-----------------|----

class RingElection:
    def __init__(self,total_process):
        self.total = total_process
        self.state = [True for x in range(self.total)]
        
    def up(self,pos):
        self.state[pos-1] = True
    
    def down(self,pos):
        self.state[pos-1] = False

    def Election(self,pos):
        if self.state[pos-1] == False:
            print(f"p{pos} cannot start election as it is down")
            return
        print(f"Election started by p{pos}")
        start = pos - 1
        ptr = (start+1) % self.total
        last_true = start 
        
        while (ptr != start):
            if self.state[ptr] == True:
                print(f"p{last_true+1} sends election message to p{ptr+1}")
                last_true = ptr 
            
            ptr = (ptr + 1) % self.total
        print(f"p{last_true+1} sends election msg to p{ptr+1}")
        max_process=max(x for x,val in enumerate(self.state) if val == True)
        print(f"Election is won by :p{max_process+1}")
        print(f"p{max_process+1} informs everyone that it is new coordinator")

class BullyElection:
    def __init__(self,total_process):
        self.total = total_process
        self.state = [True for x in range(self.total)]
    
    def up(self,pos):
        self.state[pos-1] = True 
        
    def down(self,pos):
        self.state[pos-1] = False 
    
    def Election(self,pos):
        if (pos > self.total): 
            return 
        if (self.state[pos-1] == False): 
            print(f"p{pos} cannot start election as it is down")
            return 
        print(f"Election started by p{pos}")
        
        for i in range(pos,self.total):
            print(f"Election message sent p{pos} to p{i+1}")
        
        for i in range(pos, self.total):
            if self.state[i] == True:
                print(f"p{i+1} responds OK to p{pos}")
        
        for i in range(pos, self.total):
            if self.state[i] == True:
                self.Election(i+1)
                return 
        max_process = max(x for x,val in enumerate(self.state) if val == True)
        print(f"Election is won by : p{max_process+1}")
        print(f"p{max_process+1} informs everyone that it is new coordinator")
        
def main():
    while(1):
        print("1.Ring Algorithm \n2.Bully Algorithm")
        choice = int(input("Enter your choice : "))
        if choice == 1:
            n = int(input("Enter total no. of process : "))
            algo = RingElection(n)
            algo.down(n)
            algo.Election(3)
        elif choice == 2:
            n = int(input("Enter total no. of process :"))
            algo = BullyElection(n)
            algo.down(n)
            algo.Election(1)
        else:
            print("Invalid Input")

main()

