library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity task1_sin_struct is
    Generic(n : integer := 4);
    Port ( Din : in STD_LOGIC_VECTOR(n-1 downto 0);
           EN : in STD_LOGIC;
           CLK : in STD_LOGIC;
           Dout : out STD_LOGIC_VECTOR(n-1 downto 0));
end task1_sin_struct;

architecture Behavioral of task1_sin_struct is
        component D_trigger
                port(
                D, EN, CLK : in std_logic;
                Q : out std_logic);
        end component;

begin
    reg: for i in n-1 downto 0 generate
        Di: D_trigger port map(D => Din(i), EN => EN, CLK => CLK, Q => Dout(i));
    end generate;
end Behavioral;
