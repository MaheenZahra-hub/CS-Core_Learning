module and_using_nor_gate (input a, input b, output y);

nor(nor1, a, a);  
nor(nor2, b, b); 
nor(y, nor1, nor2);

endmodule