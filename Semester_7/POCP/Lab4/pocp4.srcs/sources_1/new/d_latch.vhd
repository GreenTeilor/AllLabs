----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 26.10.2024 17:35:16
-- Design Name: 
-- Module Name: d_latch - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity d_latch is
    Port ( D : in STD_LOGIC;
           EN : in STD_LOGIC;
           Q : out STD_LOGIC);
end d_latch;

architecture Behavioral of d_latch is

begin
    Q <= D when (EN = '1');

end Behavioral;
