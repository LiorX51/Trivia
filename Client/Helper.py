ERROR =  '00000001'
LOGIN =  '00000010'
SIGNUP = '00000011'


def log_ser(list1):

    final_str = ""
    user_pass = ""

    code = LOGIN

    final_str += code + '$'

    for i in list1:

        a_byte_array = bytearray(i, "utf8")

        byte_list = []

        for byte in a_byte_array:
            binary_representation = bin(byte)

            byte_list.append(binary_representation)

        user_pass += ''.join(byte_list).replace("0b", "0") + '$'

    final_str += (bin(len(user_pass)) + '').replace('b', '') + '$' + user_pass

    return final_str[:-1]


def sign_ser(list1):

    final_str = ""
    user_pass_email = ""

    code = SIGNUP

    final_str += code + '$'

    for i in list1:
        a_byte_array = bytearray(i, "utf8")

        byte_list = []

        for byte in a_byte_array:
            binary_representation = bin(byte)

            byte_list.append(binary_representation)

        user_pass_email += ''.join(byte_list).replace("0b", "0") + '$'

    final_str += (bin(len(user_pass_email)) + '').replace('b', '') + '$' + user_pass_email

    return final_str[:-1]


def binary_to_decimal(binary):
    binary1 = binary
    decimal, i, n = 0, 0, 0
    while binary != 0:
        dec = binary % 10
        decimal = decimal + dec * pow(2, i)
        binary = binary // 10
        i += 1
    return decimal


def log_des(buffer):
    str_data = ''
    list1 = buffer.split("$")
    r_list = []
    for element in list1[2:]:
        for i in range(0, len(element), 7):
            temp_data = int(element[i:i + 7])
            decimal_data = binary_to_decimal(temp_data)
            str_data = str_data + chr(decimal_data)

        r_list.append(str_data)
        str_data = ''

    return r_list


def sign_des(buffer):
    str_data = ''
    list1 = buffer.split("$")
    r_list = []
    for element in list1[2:]:
        for i in range(0, len(element), 7):
            temp_data = int(element[i:i + 7])
            decimal_data = binary_to_decimal(temp_data)
            str_data = str_data + chr(decimal_data)

        r_list.append(str_data)
        str_data = ''

    return r_list
