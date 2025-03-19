library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity RS_latch_param is
    Port ( S, R : in STD_LOGIC;
           Q, nQ : out STD_LOGIC);
end RS_latch_param;

architecture Param of RS_latch_param is
signal q1_s, q2_s: STD_LOGIC;
begin
    q2_s <= R nor q1_s after 3 ns;
	q1_s <= S nor q2_s after 3 ns;
	nQ <= transport q1_s after 3 ns;
	Q <= transport q2_s after 3 ns;
end Param;
