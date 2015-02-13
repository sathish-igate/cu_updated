#!/bin/sh
#
# Cloud Hook: post-code-deploy
#
# Run drush updates

site="$1"
target_env="$2"
source_branch="$3"
deployed_tag="$4"
repo_url="$5"
repo_type="$6"

if [ -z "$site$target_env" ]; then
  alias=""
else
  alias="@$site.$target_env"
fi

drush $alias cc drush
drush $alias -y fra
drush $alias -y updb
drush $alias -y fra
drush $alias cc all
