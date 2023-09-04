# in depth wiki

## github actions

[github's explanation](https://docs.github.com/en/actions/quickstart)
[wokwi github actions](https://docs.wokwi.com/wokwi-ci/getting-started)

### testing github actions:  
download [act](https://github.com/nektos/act)

test github action:  
`mkdir /temp/artifacts`  
`sudo ~/bin/act -s WOKWI_CLI_TOKEN=[<get token>] --artifact-server-path /tmp/artifacts`  
> Note: probs wont work cuz token is wrong or something

[random error when running act](https://github.com/nektos/act/issues/329#issuecomment-1187246629)

finding where it is in git:  
![github actions](../../pics/github_actions.png)


### auto deploy page

[travis auto deploy docs](https://www.freecodecamp.org/news/learn-how-to-automate-deployment-on-github-pages-with-travis-ci/)

## pigweed links

[main pg](https://pigweed.dev/)
[gud yt vid that explains pigweed](https://www.youtube.com/watch?v=EyLXoWTB_c4)
[getting started guide](https://pigweed.dev/docs/getting_started.html#express-setup)
* [idk some related repo](https://pigweed.googlesource.com/pigweed/sample_project/+/main/README.md#Tokenized-Logging)

[pi pico guide](https://pigweed.dev/targets/rp2040/target_docs.html)
[pi pico guide but better?](https://pigweed.dev/targets/rp2040_pw_system/target_docs.html)
* [module that its build off of](https://pigweed.dev/targets/rp2040_pw_system/target_docs.html)
* [module that its also build off of](https://pigweed.dev/pw_system/#target-bringup)
[simulate pico](https://pigweed.dev/targets/host_device_simulator/target_docs.html)
[better pico cli](https://pigweed.dev/pw_console/py/pw_console/docs/user_guide.html#module-pw-console-user-guide)
[pico project template](https://github.com/kaycebasques/pw_template/tree/main)

[vs code integration](https://pigweed.dev/docs/editors.html#docs-editors)
[code covarge](https://pigweed.dev/build_system.html#code-coverage)
[auto setup tool chain](https://pigweed.dev/pw_env_setup/#using-pw-env-setup-in-your-project)
