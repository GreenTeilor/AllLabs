library IEEE;
use IEEE.STD_LOGIC_1164.all;

entity JK_flip_flop is
	port(
		j, k, clk : in STD_LOGIC;
		q : out STD_LOGIC
	);
end JK_flip_flop;

architecture Behavioral of JK_flip_flop is
	signal q_t: STD_LOGIC;
begin
	process(j, k, clk)
	begin
		if rising_edge(clk) then 
			if (j = '1' and k = '1') then
				q_t <= not q_t;
			elsif k = '1' then
				q_t <= '0';
			elsif j = '1' then
				q_t <= '1';
			end if; 
		end if;
	end process; 
	
	q <= q_t;
end Behavioral;