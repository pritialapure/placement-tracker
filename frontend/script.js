// The C++ backend (main_server.cpp) listens here. Change this if you run
// the server on a different port.
const API_BASE = "http://localhost:8080/api";

let allJobs = [];

// ---------- Tabs ----------

document.querySelectorAll(".tab-btn").forEach(btn => {
  btn.addEventListener("click", () => {
    document.querySelectorAll(".tab-btn").forEach(b => b.classList.remove("active"));
    document.querySelectorAll(".panel").forEach(p => p.classList.remove("active"));
    btn.classList.add("active");
    document.getElementById(btn.dataset.tab).classList.add("active");
  });
});

// ---------- Status pill styling ----------

function statusPillClass(status) {
  if (["Selected", "Offer Accepted"].includes(status)) return "success";
  if (["Rejected", "Offer Declined"].includes(status)) return "danger";
  if (status === "Not Applied") return "neutral";
  return "progress";
}

// ---------- Server status check ----------

async function checkServer() {
  const dot = document.querySelector("#serverStatus .dot");
  const text = document.getElementById("serverStatusText");
  try {
    const res = await fetch(`${API_BASE}/jobs`);
    if (res.ok) {
      dot.classList.add("online");
      text.textContent = "Connected to backend";
      return true;
    }
  } catch (e) {
    // server not reachable
  }
  dot.classList.remove("online");
  text.textContent = "Backend not running (start placement_server.exe)";
  return false;
}

// ---------- Dashboard ----------

async function loadDashboard() {
  try {
    const res = await fetch(`${API_BASE}/dashboard`);
    const data = await res.json();

    document.querySelector("#totalStamp .stamp-number").textContent = data.totalJobs;

    const cards = [
      ["Not Applied", data.notApplied],
      ["Applied", data.applied],
      ["OA Scheduled", data.oaScheduled],
      ["OA Completed", data.oaCompleted],
      ["Technical Interview", data.technicalInterview],
      ["HR Interview", data.hrInterview],
      ["Selected", data.selected],
      ["Rejected", data.rejected],
      ["Offer Accepted", data.offerAccepted],
      ["Offer Declined", data.offerDeclined],
    ];

    document.getElementById("dashboardCards").innerHTML = cards.map(([label, value]) => `
      <div class="stat-card">
        <div class="value">${value}</div>
        <div class="label">${label}</div>
      </div>
    `).join("");
  } catch (e) {
    console.error("Failed to load dashboard:", e);
  }
}

// ---------- Jobs table ----------

async function loadJobs() {
  try {
    const res = await fetch(`${API_BASE}/jobs`);
    allJobs = await res.json();
    renderJobsTable();
  } catch (e) {
    console.error("Failed to load jobs:", e);
  }
}

function renderJobsTable() {
  const search = document.getElementById("searchCompany").value.trim().toLowerCase();
  const statusFilter = document.getElementById("filterStatus").value;

  const filtered = allJobs.filter(job => {
    const matchesSearch = !search || job.companyName.toLowerCase().includes(search);
    const matchesStatus = !statusFilter || job.status === statusFilter;
    return matchesSearch && matchesStatus;
  });

  const tbody = document.getElementById("jobsTableBody");
  const emptyState = document.getElementById("emptyState");

  if (filtered.length === 0) {
    tbody.innerHTML = "";
    emptyState.hidden = false;
    return;
  }
  emptyState.hidden = true;

  tbody.innerHTML = filtered.map(job => `
    <tr>
      <td class="mono">${job.jobId}</td>
      <td>${escapeHtml(job.companyName)}</td>
      <td>${escapeHtml(job.role)}</td>
      <td class="mono">${escapeHtml(job.packageCTC)}</td>
      <td class="mono">${escapeHtml(job.deadline)}</td>
      <td>
        <select class="status-select" data-id="${job.jobId}" data-current="${escapeHtml(job.status)}">
          ${["Not Applied","Applied","OA Scheduled","OA Completed","Technical Interview","HR Interview","Selected","Rejected","Offer Accepted","Offer Declined"]
            .map(s => `<option value="${s}" ${s === job.status ? "selected" : ""}>${s}</option>`).join("")}
        </select>
      </td>
      <td class="row-actions">
        <button class="icon-btn delete-btn" data-id="${job.jobId}" title="Delete">Delete</button>
      </td>
    </tr>
  `).join("");

  document.querySelectorAll(".status-select").forEach(select => {
    select.addEventListener("change", async () => {
      const id = select.dataset.id;
      await updateStatus(id, select.value);
    });
  });

  document.querySelectorAll(".delete-btn").forEach(btn => {
    btn.addEventListener("click", async () => {
      if (confirm("Delete this job entry? This cannot be undone.")) {
        await deleteJob(btn.dataset.id);
      }
    });
  });
}

function escapeHtml(str) {
  const div = document.createElement("div");
  div.textContent = str ?? "";
  return div.innerHTML;
}

async function updateStatus(id, newStatus) {
  try {
    await fetch(`${API_BASE}/jobs?id=${id}`, {
      method: "PUT",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ status: newStatus })
    });
    await loadJobs();
    await loadDashboard();
  } catch (e) {
    alert("Could not update status — is the backend running?");
  }
}

async function deleteJob(id) {
  try {
    await fetch(`${API_BASE}/jobs?id=${id}`, { method: "DELETE" });
    await loadJobs();
    await loadDashboard();
  } catch (e) {
    alert("Could not delete job — is the backend running?");
  }
}

document.getElementById("searchCompany").addEventListener("input", renderJobsTable);
document.getElementById("filterStatus").addEventListener("change", renderJobsTable);
document.getElementById("refreshBtn").addEventListener("click", () => {
  loadJobs();
  loadDashboard();
  checkServer();
});

// ---------- Add job form ----------

document.getElementById("addJobForm").addEventListener("submit", async (e) => {
  e.preventDefault();
  const form = e.target;
  const feedback = document.getElementById("addFeedback");

  const payload = {
    jobId: Number(form.jobId.value),
    companyName: form.companyName.value,
    role: form.role.value,
    jobDescription: form.jobDescription.value,
    requiredSkills: form.requiredSkills.value,
    packageCTC: form.packageCTC.value,
    location: form.location.value,
    employmentType: form.employmentType.value,
    minCGPA: Number(form.minCGPA.value) || 0,
    eligibleBranches: form.eligibleBranches.value,
    deadline: form.deadline.value,
    applicationLink: form.applicationLink.value,
    source: form.source.value,
    resumeUsed: "",
    status: form.status.value,
    interviewRound: "None",
    notes: form.notes.value,
    dateAdded: new Date().toISOString().split("T")[0]
  };

  try {
    const res = await fetch(`${API_BASE}/jobs`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(payload)
    });

    if (res.ok) {
      feedback.textContent = "Job added successfully.";
      feedback.className = "feedback ok";
      form.reset();
      await loadJobs();
      await loadDashboard();
    } else {
      feedback.textContent = "Server rejected the request.";
      feedback.className = "feedback err";
    }
  } catch (e) {
    feedback.textContent = "Could not reach backend — start placement_server.exe first.";
    feedback.className = "feedback err";
  }
});

// ---------- Init ----------

(async function init() {
  await checkServer();
  await loadDashboard();
  await loadJobs();
})();
