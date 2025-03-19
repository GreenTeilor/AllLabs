library IEEE;
use IEEE.STD_LOGIC_1164.all;

entity RS_flip_flop is
	port(
		r, s, clk : in STD_LOGIC;
		q : out STD_LOGIC
	);
end RS_flip_flop;

architecture Behavioral of RS_flip_flop is
	signal result: STD_LOGIC;
begin
	process(r, s, clk)
	begin
		if rising_edge(clk) then
			if (r = '1' and s = '1') then
				result <= 'Z';
			elsif r = '1' then
				result <= '0';
			elsif s = '1' then
				result <= '1';
			end if; 
		end if;
	end process; 
	
	q <= result;
end Behavioral;