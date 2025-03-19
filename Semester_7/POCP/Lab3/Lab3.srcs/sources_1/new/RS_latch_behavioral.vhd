library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity RS_latch_behavioral is
    Port ( S, R : in STD_LOGIC;
           Q, nQ : out STD_LOGIC);
end RS_latch_behavioral;

architecture Behavioral of RS_latch_behavioral is
signal q1_s, q2_s: STD_LOGIC;
begin
    q2_s <= R nor q1_s;
	q1_s <= S nor q2_s;
	nQ <= q1_s;
	Q <= q2_s;
end Behavioral;
