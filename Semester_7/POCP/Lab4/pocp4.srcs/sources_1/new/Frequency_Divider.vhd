library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Frequency_Divider is
    Port ( CLK : in STD_LOGIC;
           RST : in STD_LOGIC;
           CLK_OUT : out STD_LOGIC);
end Frequency_Divider;

architecture Behavioral of Frequency_Divider is
signal res: std_logic := '0';
signal counter : integer := 0;
    constant DIV_FACTOR : integer := 50000000;
begin
    process(CLK, RST)
    begin
        if RST = '1' then
            counter <= 0;
            CLK_OUT <= '0';
        elsif rising_edge(CLK) then
            if counter = DIV_FACTOR - 1 then
                counter <= 0;
                res <= not res; 
            else
                counter <= counter + 1;
            end if;
        end if;
        CLK_OUT <= res; 
    end process;
end Behavioral;
