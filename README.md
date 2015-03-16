# BrowserHistory
Implementation of an Internet Explorer plugin to help you save the textual content of sites you browse (as you browse them).

To install, put in a directory (i.e: Program Files\BrowserHistory) and run regsvr32 on the DLL.

This plugin saves the content of all visited pages to the "BrowserHistory" directory in your Temporary Internet Files. To
keep them long term, set up a scheduled job to copy them to a more appropriate directory (like "My Documents").

Here's a snippet I have in my PowerShell profile to create a job to automatically copy the files every 5 minutes.
I put it in my profile so that the job will get automatically recreated if I accidentally delete the task.

```powershell
if(-not (Get-ScheduledJob -Name BrowserHistory -ErrorAction Ignore))
{
	$t = New-ScheduledTaskTrigger -Once -At (Get-Date) `
		-RepetitionInterval (New-TimeSpan -Minutes 5) `
		-RepetitionDuration ([TimeSpan]::MaxValue)
	Register-ScheduledJob -ScriptBlock {
		$source = "~\AppData\LocalLow\BrowserHistory"
		$destination = [Environment]::GetFolderPath("MyDocuments")

		Move-Item $source $destination -Force
	} -Trigger $t -Name BrowserHistory -MaxResultCount 1
}
```