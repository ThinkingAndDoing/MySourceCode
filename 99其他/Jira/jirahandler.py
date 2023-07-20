#!/usr/bin/python
# -*- coding:utf-8 -*-

# reference: https://jira.readthedocs.io/en/latest/
from jira import JIRA
import sys, os


class JiraTool:
    def __init__(self):
        # self.server = 'urlOfJira'
        self.basic_auth = ("username", "pwd")
        self.jiraClinet = None

    def login(self):
        self.jiraClinet = JIRA(server=self.server, basic_auth=self.basic_auth)
        if self.jiraClinet != None:
            return True
        else:
            return False

    def findIssueById(self, issueId):
        if issueId:
            if self.jiraClinet == None:
                self.login()
            return self.jiraClinet.issue(issueId)
        else:
            return "Please input your issueId"

    def createIssue(self, description, assignee, project, parent, filepath):
        issue_dict = {
            "project": {"key": project},
            "issuetype": {"name": "Review Subtask"},
            "parent": {"key": parent},
            "summary": "[xxx]Auto sync file %s from storage-cnn to storage"
            % (filepath),
            "description": description,
            "assignee": {"name": assignee},
            "components": [{"name": "wrn_hmi"}],
            "priority": {"name": "Major"},
        }
        if self.jiraClinet == None:
            self.login()
        return self.jiraClinet.create_issue(issue_dict)

    def classify(self, issueId):
        if issueId:
            if self.jiraClinet == None:
                self.login()
            currentIssue = self.jiraClinet.issue(issueId)
            self.jiraClinet.transition_issue(
                currentIssue,
                "391",
                customfield_11307={"value": "Test"},
                customfield_11312={"value": "No"},
            )
        else:
            return "Please input your issueId"

    def printAvailableNextStatus(self, issueId):
        if issueId:
            if self.jiraClinet == None:
                self.login()
            currentIssue = self.jiraClinet.issue(issueId)
            transitions = jiraTool.jiraClinet.transitions(currentIssue)
            print([(t["id"], t["name"]) for t in transitions])
        else:
            return "Please input your issueId"

    def searchIssuesByJiraCmd(self, jiraCmd):
        if self.jiraClinet == None:
            self.login()
        cye_proj_issues_of_mine = jiraTool.jiraClinet.search_issues(jiraCmd)
        print(cye_proj_issues_of_mine)


if __name__ == "__main__":
    jiraTool = JiraTool()
    jiraTool.login()

    # jiraTool.searchIssuesByJiraCmd('project = CYE AND issuetype in standardIssueTypes() AND resolution = Unresolved AND fixVersion in (V13.20.pre01, V23.20.pre01) AND assignee in (currentUser()) ORDER BY fixVersion ASC, status DESC, priority DESC, updated DESC')

    # jiraTool.printAvailableNextStatus("CYE-25865")

    # jiraTool.classify("CYE-20544")

    jiraTool.createIssue("Code Review", "uidp8103", "CYE", "CYE-25865", "")  # 1684459
