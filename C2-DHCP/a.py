import subprocess

host = '192.168.60.92'
user = 'pict'
cmd  = 'sudo apt-get install docker.io -y'

try:
    sshCmd = f'ssh {user}@{host} -S pict"{cmd}"'
    subprocess.check_call(sshCmd, shell=True)
    print("Docker has been successfully installed on the remote system.")
except subprocess.CalledProcessError as e :
    print(f"Installation failed with error code {e.returncode}. Error message: {e.output}")
except Exception as e:
    print(f"An error occured: {str(e)}")