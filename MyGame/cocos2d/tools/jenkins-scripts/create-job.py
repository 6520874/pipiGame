#create ghprb job by pr number

import os
import sys
import json
import requests

#get pr number from cmd
pr_num = sys.argv[1]

#get github access token
access_token = os.environ['GITHUB_ACCESS_TOKEN']

#get pr data via github api

api_get_pr = "https://api.github.com/repos/cocos2d/cocos2d-x/pulls/"+str(pr_num)+"?access_token="+access_token

r = requests.get(api_get_pr)
pr = r.json()

#forge a payload
payload = {"action":"open","number":"","pull_request":""}
payload['number']=pr_num
payload['pull_request']=pr

jenkins_trigger_url="http://ci.cocos2d-x.org:8000/job/cocos-2dx-pull-request-build/buildWithParameters?token="+access_token

#send trigger and payload
post_data = {'payload':""}
post_data['payload']=json.dumps(payload)
requests.post(jenkins_trigger_url, data=post_data)
