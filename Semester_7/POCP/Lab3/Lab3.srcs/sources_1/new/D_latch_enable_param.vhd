library IEEE, lcdf_vhdl;
use IEEE.STD_LOGIC_1164.ALL, lcdf_vhdl.func_prims.all;

entity D_latch_enable_param is
    Port ( e, d : in STD_LOGIC;
           q, nq : out STD_LOGIC);
end D_latch_enable_param;

architecture Param of D_latch_enable_param is
attribute dont_touch : string;
attribute dont_touch of Param : architecture is "true";
signal data : std_logic;
begin
    data <= d when (e = '1');
	q <= data after 2 ns;
	nq <= not data after 3 ns;
end Param;
