const API = {
    toggle: (led) => `/toggle${led}`,
    status: (led) => `/status${led}`,
    system: '/system'
};

let isRequesting = false;

async function fetchWithTimeout(url, timeout = 5000) {
    const controller = new AbortController();
    const id = setTimeout(() => controller.abort(), timeout);
    
    try {
        const response = await fetch(url, { signal: controller.signal });
        clearTimeout(id);
        return response;
    } catch (error) {
        clearTimeout(id);
        throw error;
    }
}

async function toggleLED(led) {
    if (isRequesting) {
        console.log('Waiting for previous request...');
        return;
    }
    
    isRequesting = true;
    const btn = document.querySelector(`.btn-toggle[data-led="${led}"]`);
    const originalText = btn.textContent;
    
    btn.textContent = '⏳';
    btn.disabled = true;
    
    try {
        const response = await fetchWithTimeout(API.toggle(led));
        const status = await response.text();
        
        const statusSpan = document.getElementById(`status${led}`);
        statusSpan.textContent = status;
        
        // Меняем текст и цвет кнопки
        if (status === 'ON') {
            btn.textContent = 'Выключить';
            btn.classList.add('active');
        } else {
            btn.textContent = 'Включить';
            btn.classList.remove('active');
        }
        
        // Визуальный эффект
        const ledCard = document.querySelector(`.led-${led}`);
        ledCard.style.borderLeft = status === 'ON' ? `4px solid #00ff88` : 'none';
        
    } catch (error) {
        console.error('Error:', error);
        const statusSpan = document.getElementById(`status${led}`);
        statusSpan.textContent = 'ERROR';
        btn.textContent = originalText;
    } finally {
        btn.disabled = false;
        isRequesting = false;
    }
}

async function updateSystemInfo() {
    try {
        const response = await fetchWithTimeout('/system');
        const data = await response.json();
        
        document.getElementById('ip').textContent = data.ip || 'unknown';
        document.getElementById('uptime').textContent = data.uptime || 0;
        document.getElementById('heap').textContent = data.heap || 0;
        
    } catch (error) {
        console.error('System info error:', error);
    }
}

function initEventListeners() {
    document.querySelectorAll('.btn-toggle').forEach(btn => {
        btn.addEventListener('click', () => {
            const led = btn.getAttribute('data-led');
            toggleLED(led);
        });
    });
}

async function init() {
    initEventListeners();
    
    // Получаем начальный статус при загрузке
    try {
        const res1 = await fetchWithTimeout(API.status(1));
        const status1 = await res1.text();
        const btn1 = document.querySelector(`.btn-toggle[data-led="1"]`);
        const span1 = document.getElementById('status1');
        span1.textContent = status1;
        if (status1 === 'ON') {
            btn1.textContent = 'Выключить';
            btn1.classList.add('active');
        } else {
            btn1.textContent = 'Включить';
            btn1.classList.remove('active');
        }
        
        const res2 = await fetchWithTimeout(API.status(2));
        const status2 = await res2.text();
        const btn2 = document.querySelector(`.btn-toggle[data-led="2"]`);
        const span2 = document.getElementById('status2');
        span2.textContent = status2;
        if (status2 === 'ON') {
            btn2.textContent = 'Выключить';
            btn2.classList.add('active');
        } else {
            btn2.textContent = 'Включить';
            btn2.classList.remove('active');
        }
    } catch (error) {
        console.error('Init error:', error);
    }
    
    await updateSystemInfo();
    
    // Обновляем только системную информацию (не трогаем кнопки)
    setInterval(updateSystemInfo, 5000);
}

if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', init);
} else {
    init();
}