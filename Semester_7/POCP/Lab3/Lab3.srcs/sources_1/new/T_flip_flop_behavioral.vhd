library IEEE;
use IEEE.std_logic_1164.all;

entity T_flip_flop_behavioral is
	port(
		t, clk, clr : in std_logic;		
		q : out std_logic
	);
end T_flip_flop_behavioral;

architecture Behavioral of T_flip_flop_behavioral is
	signal s: std_logic;
begin
	process(t, clk, clr)
	begin
		if clr = '1' then
			s <= '0';
		elsif t = '1' then
			if rising_edge(clk) then
				s <= not s;	 
			end if;
		end if;
	end process; 
	
	q <= s;
end Behavioral;