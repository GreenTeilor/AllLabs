library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity task3_1 is
    Generic(n : integer := 4);
    Port ( CLK : in STD_LOGIC;
           RST : in STD_LOGIC;
           Pout : out STD_LOGIC_VECTOR(0 to n-1));
end task3_1;

architecture Behavioral of task3_1 is
        signal register_state: std_logic_vector(0 to n-1);
begin
    Main: process (CLK, RST)
    begin
        if RST = '1' then
            register_state <= (others => '0');
        elsif rising_edge(CLK) then
            register_state <= not(register_state(N-1)) & register_state(0 to N-2);
        end if;
    end process; 
    Pout <= register_state;
end Behavioral;
