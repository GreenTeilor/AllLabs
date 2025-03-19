library IEEE, lcdf_vhdl;
use IEEE.STD_LOGIC_1164.ALL, lcdf_vhdl.func_prims.all;

entity D_latch_enable_behavioral is
    Port ( e, d : in STD_LOGIC;
           q, nq : out STD_LOGIC);
end D_latch_enable_behavioral;

architecture Behavioral of D_latch_enable_behavioral is
attribute dont_touch : string;
attribute dont_touch of Behavioral : architecture is "true";
signal data : std_logic;
begin
    data <= d when (e = '1');
	q <= data;
	nq <= not data;
end Behavioral;
