''' Generator - 
	This module generates C code, based on time_resp.json as input.
	The generated C code is used to unpack and pack 8/4 Byte streams

	References:
	https://docs.python.org/3/library/dataclasses.html
	https://docs.python.org/3/tutorial/errors.html
'''

from dataclasses import dataclass
from bottle import template as btl_template #The templating library


@dataclass(order=False, unsafe_hash=False, frozen=False)
class Desc_Fields:
	'''The unique fields in the given descriptor file, assuming a 8 Byte stream

	Args:
	  name: Name of the field
	  start_bit: starting position from 0
	  bit_length: length of the field
	  offset: after extracting the offset that needs to be added
	  scale: currently 1 by default
	  c_type: c data type

	Returns: 
	  Creates model of input data

	Raises:
	  ValueError: If an invalid value is given
	'''
	name: str
	start_bit: int 
	bit_length: int 
	offset: int
	scale: int 
	c_type: str

	def __post_init__(self):
		#TODO: Remove Magic number 63 with constant
		if self.start_bit > 63:
			raise ValueError("start_bit cannot be longer than 63 i.e 8Bytes")
		if self.start_bit < 0:
			raise ValueError("start_bit cannot be lesser than 0")
		if self.bit_length < 0:
			raise ValueError("bit_length cannot be lesser than 0")			
		if (self.start_bit + self.bit_length) > 63:
			raise ValueError("This field will overflow 8Bytes boundary, \
				\n check the bit_length and start_bit")
		if self.offset < 0:
			raise ValueError("offset cannot be lesser than 0")	
		if self.scale != 1:
			raise ValueError("The supported scale is only 1")
		if self.c_type not in {"uint8_t", "uint16_t", "uint32_t", "uint64_t"}:
			raise ValueError("Invalid c datatype is provided")
		#TODO 8: Check if bit_length and respective datatype are matching and \
		#TODO 9:  Check if this data type and fit in the remaining space


if __name__ == '__main__':
	import json
	from pprint import pprint

	print("Starting Generator.py")

	with open('./scripts/time_res.json') as f:
		descriptor = json.load(f)

	desc = [Desc_Fields(*fields.values()) for fields in descriptor['fields'] ]
	print("Parsed json descriptor:")
	#pprint(desc)

	with open('./scripts/template.txt','r') as f:
		c_template = f.read()
	c_template = c_template.replace("A TEMPLATE FILE","AN AUTO-GENERATED FILE",) 

	#print(btl_template(clk_template,desc=desc))

	with open('./src/clockp_autogen.c','w+') as f:
		f.write(btl_template(c_template,desc=desc,max_size=4))

	print("successfully generated the source file ./src/clockp_autogen.c ")


