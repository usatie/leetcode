{ pkgs, lib, config, inputs, ... }:

{
  # https://devenv.sh/packages/
  packages = [ pkgs.git ];
  languages.cplusplus = {
    enable = true;
  };
}
