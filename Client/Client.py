import socket
import Helper

SERVER_IP = "127.0.0.1"
SERVER_PORT = 666

PASSWORD = 18204

MENU_OPT = ["EXIT", "LOGIN", "SIGN UP"]
MENU_NUM_OPT = ['1', '2', '3']


def menu():
	userOpt = ''

	while userOpt not in MENU_OPT and userOpt not in MENU_NUM_OPT:
		print("\n")
		print("Type what do you want")
		print("- SIGN UP [1]")
		print("- LOGIN [2]")
		print("- EXIT [3]")
		userOpt = str(input("->"))

	return userOpt


def main():
	sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	server_address = (SERVER_IP, SERVER_PORT)
	sock.connect(server_address)

	server_msg = sock.recv(1024)
	server_msg = server_msg.decode()
	print(server_msg)

	userOpt = menu()
	while userOpt != 'EXIT' and userOpt != '3':
		if userOpt == 'LOGIN' or userOpt == '2':
			print('Enter your username:')
			username = str(input('->'))
			print('Enter your password:')
			password = str(input('->'))
			list1 = [username, password]
			print(Helper.log_ser(list1))
			sock.sendall(Helper.log_ser(list1).encode())
		elif userOpt == 'SIGN UP' or userOpt == '1':
			print('Enter your username:')
			username = str(input('->'))
			print('Enter your password:')
			password = str(input('->'))
			print('Enter your email')
			email = str(input('->'))
			list1 = [username, password, email]
			sock.sendall(Helper.sign_ser(list1).encode())

		server_msg = sock.recv(1024)
		server_msg = server_msg.decode()
		server_msg = Helper.log_des(server_msg)
		print(server_msg)
		userOpt = menu()


if __name__:
	main()

