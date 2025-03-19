library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity D_flip_flop_behavioral is 
	port (
		d, clk: in std_logic;
		q: out std_logic
	);
end D_flip_flop_behavioral;

architecture Behavioral of D_flip_flop_behavioral is		   
	signal s : std_logic;
begin
	process(d, clk)
	begin		
		if rising_edge(clk) then
			s <= d;
		end if;
	end process;
	q <= s;
end Behavioral;