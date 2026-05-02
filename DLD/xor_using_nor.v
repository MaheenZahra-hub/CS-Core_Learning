module xor_using_nor(input a, input b, output y);

nor(nor1, a, a);  
nor(nor2, b, b); 
nor(nor3, a, nor2);  
nor(nor4, b, nor1); 
nor(xor_outt, nor3, nor4); 
nor(y, xor_outt, xor_outt); 

endmodule