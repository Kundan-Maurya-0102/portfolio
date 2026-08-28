/* =========================================================
   KUNDAN KUMAR PORTFOLIO
   Main JavaScript
   ========================================================= */

document.addEventListener("DOMContentLoaded", () => {

  /* =======================================================
     SMOOTH SCROLLING
     ======================================================= */

  const navigationLinks = document.querySelectorAll(
    '.navbar a[href^="#"]'
  );

  navigationLinks.forEach((link) => {

    link.addEventListener("click", (event) => {

      const targetId = link.getAttribute("href");

      const target = document.querySelector(targetId);

      if (!target) return;

      event.preventDefault();

      target.scrollIntoView({
        behavior: "smooth",
        block: "start"
      });

    });

  });


  /* =======================================================
     ACTIVE NAVIGATION LINK
     ======================================================= */

  const sections = document.querySelectorAll("section[id]");
  const navLinks = document.querySelectorAll(".navbar nav a");

  const updateActiveLink = () => {

    let currentSection = "";

    sections.forEach((section) => {

      const sectionTop = section.offsetTop - 150;
      const sectionHeight = section.offsetHeight;

      if (
        window.scrollY >= sectionTop &&
        window.scrollY < sectionTop + sectionHeight
      ) {

        currentSection = section.getAttribute("id");

      }

    });


    navLinks.forEach((link) => {

      link.classList.remove("active");

      const linkTarget = link.getAttribute("href");

      if (linkTarget === `#${currentSection}`) {
        link.classList.add("active");
      }

    });

  };


  window.addEventListener(
    "scroll",
    updateActiveLink,
    { passive: true }
  );

  updateActiveLink();


  /* =======================================================
     SCROLL REVEAL ANIMATION
     ======================================================= */

  const revealElements = document.querySelectorAll(
    ".section-heading, .about-grid, .timeline-item, .skill-card, .project-card, .certificate, .career-card, .contact-card"
  );

  const revealObserver = new IntersectionObserver(
    (entries, observer) => {

      entries.forEach((entry) => {

        if (!entry.isIntersecting) return;

        entry.target.classList.add("visible");

        observer.unobserve(entry.target);

      });

    },
    {
      threshold: 0.12
    }
  );


  revealElements.forEach((element) => {

    element.classList.add("reveal-element");

    revealObserver.observe(element);

  });


  /* =======================================================
     CURRENT YEAR
     ======================================================= */

  const footerYear = document.querySelector(
    "footer .footer-content p"
  );

  if (footerYear) {

    const currentYear = new Date().getFullYear();

    footerYear.textContent =
      `© ${currentYear} Kundan Kumar`;

  }


  /* =======================================================
     EXTERNAL LINK SECURITY
     ======================================================= */

  const externalLinks = document.querySelectorAll(
    'a[target="_blank"]'
  );

  externalLinks.forEach((link) => {

    link.setAttribute(
      "rel",
      "noopener noreferrer"
    );

  });


  /* =======================================================
     KEYBOARD ACCESSIBILITY
     ======================================================= */

  document.addEventListener("keydown", (event) => {

    if (event.key === "Escape") {

      document.activeElement?.blur();

    }

  });

});
