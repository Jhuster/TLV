TLV
----------

TLV is the representative of type-length-value. It's used in many data communication protocols. 

Here is some description of TLV format: https://en.wikipedia.org/wiki/Type-length-value

This project aims to provide some easy-to-use API for TLV encode and decode in C/C++/Java and some other languages.

Brief
----------

One TLV Box is shown as follow:
 
   4Bytes     4Bytes     $Length Bytes
+----------+----------+-----------------+
|   Type   |  Length  |      Value      |
+----------+----------+-----------------+

And serial TLV boxes can be connected as follow:

   4Bytes     4Bytes     $Length Bytes     4Bytes     4Bytes     $Length Bytes
+----------+----------+-----------------+----------+----------+-----------------+
|   Type   |  Length  |      Value      |   Type   |  Length  |      Value      |
+----------+----------+-----------------+----------+----------+-----------------+

Contact
----------
Email：lujun.hust@gmail.com
